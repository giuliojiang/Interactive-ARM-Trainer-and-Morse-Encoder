import java.io.File;
import java.io.IOException;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class IvanHandlerAll implements EventHandler<ActionEvent> {
	
	protected String ivanPath;
	protected String command;
	
	public IvanHandlerAll(String ivanPath)
	{
		this.ivanPath = ivanPath;
		this.command = ivanPath + " -s";
	}
	
	@Override
	public void handle(ActionEvent arg0) {
		Runtime r = Runtime.getRuntime();
		if (new File(ivanPath).isFile()) {
			try {
				r.exec("xterm -hold -e " + command);
			} catch (IOException e) {
				System.out.println("Error while executing system command.");
				System.exit(1);
			}
		} else {
			final Stage dialog = new Stage();
			
			GridPane dialogGrid = new GridPane();
			dialogGrid.setAlignment(Pos.CENTER);
			dialogGrid.setHgap(10);
			dialogGrid.setVgap(10);
			dialogGrid.setPadding(new Insets(30, 30, 30, 30));
			
			Text dialogText = new Text();
			dialogText.setText("Could not start trainer_branch\n"
					+ "Have you compiled it?");
			dialogGrid.add(dialogText, 0, 0);
			
			Button dialogButton = new Button();
			dialogButton.setText("OK");
			dialogGrid.add(dialogButton, 0, 1);
			dialogButton.setOnAction(new EventHandler<ActionEvent>(){
				@Override
				public void handle(ActionEvent arg0) {
					dialog.close();
				}
			});
			
			Scene dialogScene = new Scene(dialogGrid, 300, 200);
			dialog.setScene(dialogScene);
			dialog.show();
		}
	}
}

