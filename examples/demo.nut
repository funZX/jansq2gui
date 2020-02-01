#! /usr/bin/jansq2gui

function Run()
{
	local r = imgui.status();

	r = imgui.begin("A");
	if (r.Show)
	{
		if (imgui.begin_child("A.a"))
		{
			
		}
		imgui.end_child();
		
		if (imgui.begin_child_id(1))
		{
			
		}
		imgui.end_child();
	}
	imgui.end();
}

function Init()
{
	jansq2gui__Run(::Run);
}

jansq2gui__Api_Init("jansq2gui demo", ::Init);