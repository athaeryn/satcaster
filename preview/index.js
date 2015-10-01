var express = require('express')
var io = require('socket.io')(server)
var exec = require('child_process').exec

var app = express()
var server = require('http').createServer(app)

app.use(express.static('public'))

app.get('/', (_, res) => {
  res.send("hello")
})

var chokidar = require('chokidar')
var watcher = chokidar.watch('main.cpp')

server.listen(process.env.NODE_ENV || 7000, function () {
  var host = server.address().address
  var port = server.address().port
  console.log('Satcaster preview server listening at http://%s:%s', host, port)

  watcher.on('all', make)
})


function make () {
  var timingLabel = 'cmake'
  console.time(timingLabel)
  exec('make -C build', function (error, stdout, stderr) {
    console.timeEnd(timingLabel)
    if (error != null) {
      console.log('exec error: %s', error)
      console.log(stdout)
      console.log(stderr)
      return
    }
    render()
  })
}

function render () {
  var timingLabel = 'render'
  console.time(timingLabel)
  var time = +new Date()
  var renderPath = 'preview/public/renders/' + time + '.bmp'
  exec('bin/satcaster scenes/simple.txt ' + renderPath, function (error, stdout, stderr) {
    console.timeEnd(timingLabel)
    console.log(stdout)
  })
}
