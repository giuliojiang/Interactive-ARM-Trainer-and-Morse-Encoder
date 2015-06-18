import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class InputStringHandler implements EventHandler<ActionEvent> {

	private String data;
	private Stage stage;
	private TextField textField;
	private String programPath;

	public InputStringHandler(Stage stage, TextField textField) {
		this.stage = stage;
		this.textField = textField;
		programPath = ClassLoader.getSystemClassLoader().getResource(".")
				.getPath();
	}

	public String getData() {
		return data;
	}

	@Override
	public void handle(ActionEvent e) {
		// get first 50 chars of the text field
		data = textField.getText();
		data = data.substring(0, Math.min(data.length(), 50));
		System.out.println(data);

		System.out.println(programPath);

		// write file to disk
		Runtime r = Runtime.getRuntime();
		Process p;
		try {
			p = r.exec("mkdir " + programPath + "/temp");
			p.waitFor();
		} catch (IOException | InterruptedException e3) {
			System.out.println("Error while creating directory");
			System.exit(1);
		}
		File txtFile = new File(programPath + "/temp/line.txt");
		PrintStream txtFileStream = null;
		try {
			txtFileStream = new PrintStream(txtFile);
		} catch (FileNotFoundException e2) {
			System.out.println("Error while creating file");
			System.exit(1);
		}
		txtFileStream.println(data);

		// create paths
		String morseEncoderPath = programPath + "MorseEncoder";
		String lineTxtPath = programPath + "temp/line.txt";
		String lineSPath = programPath + "temp/line.s";
		String kernelPath = programPath + "temp/kernel.img";
		String assemblerPath = programPath + "../../src/assemble";
		String emulatorPath = programPath + "../../src/emulate";

		// forward commands to system
		try {
			// morse encode
			System.out.println(morseEncoderPath + " " + lineTxtPath + " "
					+ lineSPath);
			p = r.exec(morseEncoderPath + " " + lineTxtPath + " " + lineSPath);
			p.waitFor();

			// assemble
			System.out.println(assemblerPath + " " + lineSPath + " " + kernelPath
					+ " -s");
			p = r.exec(assemblerPath + " " + lineSPath + " " + kernelPath
					+ " -s");
			p.waitFor();
		} catch (IOException | InterruptedException e1) {
			System.out.println("Error occurred in system call");
			System.exit(1);
		}

		// close stage
		stage.close();

		// make new scene =====================================
		// ====================================================

		// create new grid
		GridPane grid = new GridPane();
		grid.setAlignment(Pos.CENTER);
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(25, 25, 25, 25));

		// text box
		Text doneText = new Text();
		doneText.setText("Your assembler file has been generated");
		grid.add(doneText, 0, 0);

		// text box
		Text finishedText = new Text();
		finishedText.setText("saved in temp/kernel.img");
		grid.add(finishedText, 0, 1);

		// label box
		Label assemblerLabel = new Label();
		String assembler = readAssembler();
		assemblerLabel.setText(assembler);

		// scrollPane
		ScrollPane scrollPane = new ScrollPane();
		grid.add(scrollPane, 0, 2, 5, 1);
		scrollPane.setContent(assemblerLabel);
		scrollPane.setPrefSize(700, 450);

		// emulate button
		Button emulateButton = new Button();
		emulateButton.setText("Emulate it!");
		emulateButton.setOnAction(new EmulateHandler(r, emulatorPath,
				kernelPath));
		grid.add(emulateButton, 0, 3);

		// quit button
		Button quitButton = new Button();
		quitButton.setText("Exit");
		quitButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent arg0) {
				stage.close();
			}
		});
		grid.add(quitButton, 1, 3);

		// setup scene and show
		Scene scene = new Scene(grid, 800, 600);
		stage.setScene(scene);

		// keyboard events
		scene.addEventHandler(KeyEvent.KEY_PRESSED,
				new EventHandler<KeyEvent>() {
					@Override
					public void handle(KeyEvent t) {
						if (t.getCode() == KeyCode.ESCAPE) {
							System.exit(0);
						}
					}
				});

		stage.show();

	}

	private String readAssembler() {
		byte[] encoded = null;
		try {
			encoded = Files.readAllBytes(Paths
					.get(programPath + "/temp/line.s"));
		} catch (IOException e) {
			System.out.println("Error in readAssembler");
			System.exit(1);
		}
		return new String(encoded, Charset.defaultCharset());
	}

}
