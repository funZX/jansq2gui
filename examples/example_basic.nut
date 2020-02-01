#! /usr/bin/jansq2gui

demo <- imgui.status();

function Run()
{
	if (demo.Open)
	{
		demo = imgui.show_demo_window(true);
	}
}

function Init()
{
	jansq2gui__Run(::Run);
}

jansq2gui__Api_Init("jansq2gui example_basic", ::Init);