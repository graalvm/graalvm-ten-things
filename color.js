var Color = require('color');

process.argv.slice(2).forEach(function (val) {
  print(Color(val).hsl().string());
});
