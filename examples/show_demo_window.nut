function Run()
{
	imgui.show_demo_window();
	imgui.show_about_window();
	imgui.show_metrics_window();
}

function Init()
{
	jansq2gui__Run(::Run);
}

jansq2gui__Api_Init("show_demo_window", 800, 600, ::Init);