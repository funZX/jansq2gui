function Run()
{
	jansq2gui.imgui_show_demo_window();
	jansq2gui.imgui_show_about_window();
	jansq2gui.imgui_show_metrics_window();
	
	jansq2gui.imgui_begin("Begin");
	
	if (jansq2gui.imgui_begin_child("BeginChild"))
	{
		jansq2gui.imgui_end_child();
	}
	
	jansq2gui.imgui_end();
}

function Init()
{
	import("util");
	
	util.Print();

	jansq2gui__Run(::Run);
}

jansq2gui__Api_Init("show_demo_window", 800, 600, ::Init);