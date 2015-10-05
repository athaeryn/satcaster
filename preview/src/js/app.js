require('babelify/polyfill');
import io from 'socket.io-client'

const socket = io()

socket.on('make', function () {
  console.log('make')
})

let img = document.getElementById('render')
console.log(img)

socket.on('render', function (timestamp) {
  img.src = `/renders/${timestamp}.bmp`
  errorOff()
})

socket.on('error', errorOn)


function errorOn () {
  document.body.classList.add('error')
}

function errorOff () {
  document.body.classList.remove('error')
}
