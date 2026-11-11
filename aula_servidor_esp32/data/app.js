const state = document.getElementById('state');
const indicator = document.getElementById('indicator');
const message = document.getElementById('message');
const buttons = [document.getElementById('turn-on'), document.getElementById('turn-off')];

function showStatus(data) {
  state.textContent = data.ligado ? 'LED ligado' : 'LED desligado';
  indicator.classList.toggle('on', data.ligado);
  message.textContent = '';
}

async function requestStatus(path, method = 'GET') {
  buttons.forEach(button => button.disabled = true);
  try {
    const response = await fetch(path, { method, cache: 'no-store' });
    if (!response.ok) throw new Error(`HTTP ${response.status}`);
    showStatus(await response.json());
  } catch (error) {
    message.textContent = `Falha na comunicação com a ESP32: ${error.message}`;
  } finally {
    buttons.forEach(button => button.disabled = false);
  }
}

buttons[0].addEventListener('click', () => requestStatus('/api/led/on', 'POST'));
buttons[1].addEventListener('click', () => requestStatus('/api/led/off', 'POST'));
requestStatus('/api/status');
