
initialized <- false
terminated  <- false

api <- jansq2gui;

function on_init_callback(_title, _width, _height) {
	print("\njansq2gui::Init");
}
initialized = api.Init("ShowDemoWindow", 800, 600, on_init_callback)




jansq2gui <- {

	function Main()
	{
		api.igShowDemoWindow();
		api.igShowAboutWindow();
		api.igShowMetricsWindow();
		
		api.igBegin("Begin")
		
		if (api.igBeginChild("BeginChild"))
		{
			api.igEndChild();
		}		
		
		if (api.igBeginChildId(1))
		{
			api.igEndChild();
		}		
		api.igEnd();
	}
}


function on_term_callback() {
	print("\njansq2gui::Term");
}
terminated = api.Term(on_term_callback)

