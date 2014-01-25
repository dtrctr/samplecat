using GLib;
using Gtk;
using Gdk;
using GL;
using GLU;
using Cairo;

[CCode(
   cheader_filename = "stdint.h",
   cheader_filename = "spectrogram.h",
   lower_case_cprefix = "", cprefix = "")]

public delegate void SpectrogramReady(char* filename, Gdk.Pixbuf* a, void* user_data_);

public extern void get_spectrogram_with_target (char* path, SpectrogramReady on_ready, void* user_data);
public extern void cancel_spectrogram          (char* path);
 
public class GlSpectrogram : Gtk.DrawingArea {
	public static GlSpectrogram instance;
	public static GLContext glcontext;

	private string _filename;
	private Gdk.Pixbuf* pixbuf = null;
	private bool gl_init_done = false;
	private GL.GLuint Textures[2];
	private const double near = 10.0;
	private const double far = -100.0;

	public GlSpectrogram ()
	{
		//print("GlSpectrogram\n");
		add_events (Gdk.EventMask.BUTTON_PRESS_MASK | Gdk.EventMask.BUTTON_RELEASE_MASK | Gdk.EventMask.POINTER_MOTION_MASK);

		set_size_request (200, 100);

		var glconfig = new GLConfig.by_mode (GLConfigMode.RGB | GLConfigMode.DOUBLE);
		WidgetGL.set_gl_capability (this, glconfig, glcontext, true, GLRenderType.RGBA_TYPE);

		instance = this;
	}

	public static void set_gl_context(GLContext _glcontext)
	{
		glcontext = _glcontext;
	}

	private void load_texture()
	{
		//print("GlSpectrogram.load_texture...\n");
		GLDrawable gldrawable = WidgetGL.get_gl_drawable(this);

		if (!gldrawable.gl_begin(glcontext)) print("gl context error!\n");
		if (!gldrawable.gl_begin(glcontext)) return;

		glBindTexture(GL_TEXTURE_2D, Textures[0]);

		Gdk.Pixbuf* scaled = pixbuf->scale_simple(256, 256, Gdk.InterpType.BILINEAR);
		//print("GlSpectrogram.load_texture: %ix%ix%i\n", scaled->get_width(), scaled->get_height(), scaled->get_n_channels());

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GL.GLint n_colour_components = (GL.GLint)scaled->get_n_channels();
		GL.GLenum format = scaled->get_n_channels() == 4 ? GL_RGBA : GL_RGB;
		if((bool)gluBuild2DMipmaps(GL_TEXTURE_2D, n_colour_components, (GL.GLsizei)scaled->get_width(), (GL.GLsizei)scaled->get_height(), format, GL_UNSIGNED_BYTE, scaled->get_pixels()))
			print("mipmap generation failed!\n");

		scaled->unref();

		gldrawable.gl_end();
	}

	public override bool configure_event (EventConfigure event)
	{
		GLDrawable gldrawable = WidgetGL.get_gl_drawable(this);

		if (!gldrawable.gl_begin(glcontext)) return false;

		glViewport(0, 0, (GLsizei)allocation.width, (GLsizei)allocation.height);

		if(!gl_init_done){
			glGenTextures(1, Textures);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Textures[0]);

			gl_init_done = true;
		}

		gldrawable.gl_end();
		return true;
	}

	public override bool expose_event (Gdk.EventExpose event)
	{
		GLDrawable gldrawable = WidgetGL.get_gl_drawable (this);

		if (!gldrawable.gl_begin (glcontext)) return false;

		set_projection(); // has to be done on each expose when using shared context.

		glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT);

		double x = 0.0;
		double w = allocation.width;
		double top = allocation.height;
		double botm = 0.0;
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0); glVertex2d(x,     top);
		glTexCoord2d(1.0, 0.0); glVertex2d(x + w, top);
		glTexCoord2d(1.0, 1.0); glVertex2d(x + w, botm);
		glTexCoord2d(0.0, 1.0); glVertex2d(x,     botm);
		glEnd();

		if (gldrawable.is_double_buffered ())
			gldrawable.swap_buffers ();
		else
			glFlush ();

		gldrawable.gl_end ();
		return true;
	}

	private void set_projection()
	{
		glViewport(0, 0, (GLsizei)allocation.width, (GLsizei)allocation.height);
		glMatrixMode((GL.GLenum)GL_PROJECTION);
		glLoadIdentity();

		double left = 0.0;
		double right = allocation.width;
		double top   = allocation.height;
		double bottom = 0.0;
		glOrtho (left, right, bottom, top, near, far);
	}

	/*
	public override bool button_press_event (Gdk.EventButton event) {
		return false;
	}

	public override bool button_release_event (Gdk.EventButton event) {
		return false;
	}

	public override bool motion_notify_event (Gdk.EventMotion event) {
		return false;
	}
	*/

	/*
	private bool on_configure_event (Widget widget, EventConfigure event)
	{
		print("on_configure_event\n");
		GLDrawable gldrawable = WidgetGL.get_gl_drawable (widget);

		if (!gldrawable.gl_begin (glcontext)) return false;

		glViewport (0, 0, (GLsizei) widget.allocation.width, (GLsizei) widget.allocation.height);

		gldrawable.gl_end ();
		return true;
	}
	*/

	public void set_file(char* filename)
	{
		//print("GlSpectrogram.set_file: %s\n", (string)filename);
		_filename = ((string*)filename)->dup();

		cancel_spectrogram(null);

		get_spectrogram_with_target(filename, (filename, _pixbuf, b) => {
			if((bool)_pixbuf){
				if((bool)pixbuf) pixbuf->unref();
				pixbuf = _pixbuf;
				load_texture();
				this.queue_draw();
			}
		}, null);
	}

#if 0
	public override void realize ()
	{
		print("GlSpectrogram.realize\n");

		/*
		this.set_flags (Gtk.WidgetFlags.REALIZED);

		var attrs = Gdk.WindowAttr ();
		attrs.window_type = Gdk.WindowType.CHILD;
		attrs.width = this.allocation.width;
		attrs.wclass = Gdk.WindowClass.INPUT_OUTPUT;
		attrs.event_mask = this.get_events() | Gdk.EventMask.EXPOSURE_MASK;
		this.window = new Gdk.Window (this.get_parent_window (), attrs, 0);

		this.window.set_user_data (this);

		this.style = this.style.attach (this.window);

		this.style.set_background (this.window, Gtk.StateType.NORMAL);
		this.window.move_resize (this.allocation.x, this.allocation.y, this.allocation.width, this.allocation.height);
		*/
		base.realize();
	}

	public override void unrealize ()
	{
		base.unrealize();
	}
#endif
}

