require 'erb'

x = 42

template = ERB.new <<-EOF
  The value of x is: <%= x %>
EOF

loop do
  puts template.result(binding)
end
