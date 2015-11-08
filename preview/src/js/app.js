require('babelify/polyfill');
import io from 'socket.io-client'
import pbm2canvas from 'pbm2canvas'

const socket = io()

const container = document.getElementById('render')

socket.on('make', function () {
  console.log('make')
})

socket.on('render', function (pbm) {
  let newCanvas = pbm2canvas(pbm)
  let oldCanvas = container.querySelector('canvas')
  if (oldCanvas) {
    container.replaceChild(newCanvas, oldCanvas)
  } else {
    container.appendChild(newCanvas)
  }
  errorOff()
})

socket.on('error', errorOn)


function errorOn () {
  document.body.classList.add('error')
}

function errorOff () {
  document.body.classList.remove('error')
}
