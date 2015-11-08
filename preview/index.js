var browserify = require('browserify-middleware')
var exec = require('child_process').exec
var spawn = require('child_process').spawn
var express = require('express')
var http = require('http')

var app = express()
var server = require('http').createServer(app)
var io = require('socket.io')(server)

app.use(express.static(__dirname + '/public'))
app.use('/app.js', browserify(__dirname + '/src/js/app.js'))

app.get('/', (_, res) => res.sendFile(__dirname + '/public/index.html'))

var chokidar = require('chokidar')
var watcher = chokidar.watch('*.cpp')
watcher.add('*.h')
watcher.add('scenes/simple.txt')

server.listen(process.env.NODE_ENV || 7000, function () {
  var host = server.address().address
  var port = server.address().port
  console.log('Satcaster preview server listening at http://%s:%s', host, port)

  watcher.on('all', make)
})


//
//Socket stuff
//
io.on('connection', function (socket) {
  console.log('browser connection')
  socket.on('disconnect', function () {
    console.log('browser disconnect')
  })
})


//
// Build process stuff
//
function make () {
  var timingLabel = 'cmake'
  console.time(timingLabel)
  exec('make -C build', function (error, stdout, stderr) {
    console.timeEnd(timingLabel)
    if (error != null) {
      console.log('exec error: %s', error)
      console.log(stdout)
      console.log(stderr)
      io.emit('error')
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
  var render = spawn('bin/satcaster', ['scenes/simple.txt'])
  var pbm = ''
  render.stdout.on('data', function (data) {
    pbm += data
  })
  render.stderr.on('data', function (data) {
    console.log('err', data)
  })
  render.on('close', function () {
    console.timeEnd(timingLabel)
    io.emit('render', pbm)
  })
}
