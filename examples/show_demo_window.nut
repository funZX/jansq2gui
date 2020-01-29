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

jansq2gui__Api_Init("show_demo_window::jansq2gui__Main", 800, 600, ::Run);