if RUBY_PLATFORM =~ /win/
  system "ruby ./src/make_windows.rb #{ ARGV.join(' ') }"
elsif RUBY_PLATFORM =~ /linux/
  if RUBY_PLATFORM =~ /x86_64/
    system "ruby ./src/make_linux.rb #{ ARGV.join(' ') }"
  else
    system "ruby ./src/make_linux32.rb #{ ARGV.join(' ') }"
  end
else
  puts "unknown platform #{RUBY_PLATFORM}"
end
