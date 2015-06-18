import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class MorseEncoderGUI extends Application {

	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		// set STAGE title
		primaryStage.setTitle("Morse Encoder");

		// create grid
		GridPane grid = new GridPane();
		grid.setAlignment(Pos.CENTER);
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(25, 25, 25, 25));

		// add welcome text
		Text welcome = new Text();
		welcome.setText("Morse Encoder");
		grid.add(welcome, 0, 0, 4, 1);
		welcome.setFont(Font.font("Sans", 20));

		// welcome group by text
		Text groupByText = new Text();
		groupByText.setText("by Group 18");
		grid.add(groupByText, 0, 1, 4, 1);
		groupByText.setFont(Font.font("Sans", 20));

		// enter your string text
		Text enterStringText = new Text();
		enterStringText.setText("Enter here the string you want to encode");
		grid.add(enterStringText, 0, 3, 4, 1);

		// input text field
		TextField stringTextField = new TextField();
		grid.add(stringTextField, 0, 4, 4, 1);

		// OK button
		Button okButton = new Button();
		okButton.setText("OK");
		okButton.setAlignment(Pos.BOTTOM_RIGHT);
		grid.add(okButton, 3, 5);

		// set button event handler
		final InputStringHandler inputHandler = new InputStringHandler(
				primaryStage, stringTextField);
		okButton.setOnAction(inputHandler);

		// setup scene
		Scene scene = new Scene(grid, 800, 600);
		primaryStage.setScene(scene);

		// keyboard events
		scene.addEventHandler(KeyEvent.KEY_PRESSED,
				new EventHandler<KeyEvent>() {
					@Override
					public void handle(KeyEvent t) {
						if (t.getCode() == KeyCode.ESCAPE) {
							System.exit(0);
						}
						if (t.getCode() == KeyCode.ENTER) {
							inputHandler.handle(null);
						}
					}
				});

		// show the WINDOW
		primaryStage.show();

	}

}
