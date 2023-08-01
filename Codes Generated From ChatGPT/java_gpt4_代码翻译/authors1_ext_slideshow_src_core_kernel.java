package slideshow;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;

public class Slideshow {

    private ArgumentSet arg;
    private PlatformBackend backend;
    private boolean running;

    public Slideshow(ArgumentSet arg) {
        this.arg = arg;
        this.backend = new PlatformBackend();
        this.running = false;
    }

    public void init() {
        initBackend();
        initGraphics();
        initIPC();
        initBrowser();
        initStateMachine();
    }

    public void cleanup() {
        cleanupIPC();
        cleanupBackend();
    }

    public void initBackend() {
        backend.init(arg.getWidth(), arg.getHeight(), arg.isFullscreen());
    }

    public void cleanupBackend() {
        backend.cleanup();
    }

    public void initGraphics() {
        Graphics.init(arg.getWidth(), arg.getHeight());
        Graphics.setTransition(arg.getTransitionString() != null ? arg.getTransitionString() : "fade");
    }

    public void initIPC() {
        // Initialize inter-process communication
    }

    public void cleanupIPC() {
        // Clean up inter-process communication
    }

    public void initBrowser() {
        // Initialize browser
    }

    public void initStateMachine() {
        // Initialize state machine
    }

    public void run() {
        start();

        while (running()) {
            poll();
            action();
        }
    }

    public void poll() {
        backend.poll();
    }

    public void action() {
        // Perform actions based on the current state
    }

    public void start() {
        running = true;
    }

    public void quit() {
        running = false;
        Log::warning("Failed to get settings from frontend: %s (%ld)\n", chunk.memory, response);
	}else

    {
		struct json_object* settings = json_tokener_parse(chunk.memory);
		if ( settings ){
			if ( json_object_is_type(settings, json_type_object) ){
				json_object_object_foreach(settings, key, val){
					Log::verbose("Settings: %s = %s\n", key, json_object_get_string(val));

					if ( strcmp(key, "queue_id") == 0 ){
						queue_set(json_object_get_int(val));
					} else if ( strcmp(key, "transition") == 0 ){
						load_transition(json_object_get_string(val));
					}
				}
			}
			json_object_put(settings);
		} else {
			Log::warning("Settings response was not valid JSON: %s\n", chunk.memory);
		}
	}

    free(chunk.memory);
}