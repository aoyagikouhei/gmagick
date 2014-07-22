require "mkmf"

if gmconfig = ( find_executable('GraphicsMagickWand-config') )
  $stderr.puts "Using config values from %s" % [ gmconfig ]
  $CPPFLAGS << " " + `"#{gmconfig}" --cppflags`.chomp
  $LDFLAGS << " " + `"#{gmconfig}" --ldflags`.chomp.sub(/ -fPIE/, '').sub(/ -pie/, '')
  $LOCAL_LIBS << " " + `"#{gmconfig}" --libs`.chomp
else
  $stderr.puts "No GraphicsMagickWand-config... trying anyway. If building fails, please try again with",
		" --with-gm-config=/path/to/GraphicsMagickWand-config"
end

create_makefile("gmagickn")
