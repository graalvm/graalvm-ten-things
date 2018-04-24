var express = require('express');
var app = express();

color_rgb = Polyglot.eval('ruby', `
  require 'color'
  Color::RGB
`);

app.get('/css/:name', function (req, res) {
  color = color_rgb.by_name(req.params.name).html()
  res.send('<h1 style="color: ' + color + '" >' + color + '</h1>');
});

app.listen(8080, function () {
  console.log('serving at http://localhost:8080')
});
