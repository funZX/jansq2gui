#! /usr/bin/jansq2gui --exec

# 1. args available for parsing like this:
print(jansq2gui.Args)


# 2. or like this
args <- ""
function Init(args)
{
	::args = args
}

jansq2gui__Api_Init("jansq2gui console app with args", ::Init);
print(::args)
