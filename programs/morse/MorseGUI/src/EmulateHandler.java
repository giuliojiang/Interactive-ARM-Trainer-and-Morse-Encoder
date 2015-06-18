import java.io.IOException;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;

public class EmulateHandler implements EventHandler<ActionEvent> {

	private Runtime run;
	private String emulatorPath;
	private String kernelPath;

	public EmulateHandler(Runtime run, String emulatorPath, String kernelPath) {
		this.run = run;
		this.emulatorPath = emulatorPath;
		this.kernelPath = kernelPath;
	}

	@Override
	public void handle(ActionEvent arg0) {
		// Process p = null;

		try {
			run.exec("xterm -hold -e" + " " + emulatorPath + " " + kernelPath);
			// p.waitFor();
		} catch (IOException e) {
			System.out.println("Error while running emulator");
		}

	}
}
