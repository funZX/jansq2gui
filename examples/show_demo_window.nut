demo <- imgui.status();

function Run()
{
	local r = imgui.status();

	r = imgui.begin("A");
	if (r.show)
	{
		imgui.end();
	}
	
	if (demo.open)
	{
		demo = imgui.show_demo_window(true);
	}
}

function Init()
{

	jansq2gui__Run(::Run);
}

jansq2gui__Api_Init("show_demo_window", 800, 600, ::Init);