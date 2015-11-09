require('babelify/polyfill');
import io from 'socket.io-client'
import pbm2canvas from 'pbm2canvas'

const socket = io()

const container = document.getElementById('render')

socket.on('make', errorOff)
socket.on('error', errorOn)
socket.on('render', function (pbm) {
  render(pbm)
  errorOff()
})

function render (pbm) {
  let newCanvas = pbm2canvas(pbm)
  let oldCanvas = container.querySelector('canvas')
  if (oldCanvas) {
    container.replaceChild(newCanvas, oldCanvas)
  } else {
    container.appendChild(newCanvas)
  }
}

function errorOn (error) {
  console.log(error)
  document.body.classList.add('error')
}

function errorOff () {
  document.body.classList.remove('error')
}
