
if RUBY_PLATFORM =~ /win/
  system "ruby ./src/make_windows.rb #{ ARGV.join(' ') }"
elsif RUBY_PLATFORM =~ /linux/
  system "ruby ./src/make_linux.rb #{ ARGV.join(' ') }"
else
  puts "unknown platform #{RUBY_PLATFORM}"
end
