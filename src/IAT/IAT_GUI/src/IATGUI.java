import java.io.File;
import java.io.IOException;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class IATGUI extends Application {

	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(final Stage stage) throws Exception {

		// detect executable path
		// String programPath = new File("").getAbsolutePath();
		String programPath = ClassLoader.getSystemClassLoader()
				.getResource(".").getPath();
		System.out.println(programPath);
		final String interpreterPath = programPath + "interpreter";
		String path = programPath + "trainer_branch";

		// set window title
		stage.setTitle("IAT Launcher");

		// create grid
		GridPane grid = new GridPane();
		grid.setAlignment(Pos.CENTER);
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(30, 30, 30, 30));

		// top text
		Text iatText = new Text();
		iatText.setText("Interactive ARM Trainer");
		grid.add(iatText, 0, 0, 8, 1);
		iatText.setFont(Font.font("Sans", 25));

		// Interpreter button
		Button interpreterBtn = new Button();
		interpreterBtn.setText("Interpreter");
		interpreterBtn.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent arg0) {
				Runtime r = Runtime.getRuntime();
				if (new File(interpreterPath).isFile()) {
					try {
						r.exec("xterm -hold -e " + interpreterPath);
					} catch (IOException e) {
						System.out
								.println("Error while executing system command.");
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
					dialogText.setText("Could not start interpreter\n"
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
		});
		grid.add(interpreterBtn, 0, 1);
		
		// Feroz's games
		Button ferozBtn = new Button();
		ferozBtn.setText("Feroz's games");
		grid.add(ferozBtn, 0, 2);
		FerozHandlerAll ferozHandlerAll = new FerozHandlerAll(path);
        ferozBtn.setOnAction(ferozHandlerAll);
		
		// levels text
		Text ferozLevelsText = new Text();
		ferozLevelsText.setText("Levels:");
		grid.add(ferozLevelsText, 1, 2);
		
		// Feroz level 1
		Button ferozBtn1 = new Button();
		ferozBtn1.setText("1");
		grid.add(ferozBtn1, 2, 2);
		FerozHandlerLevel ferozHandler1 = new FerozHandlerLevel(path, 9);
		ferozBtn1.setOnAction(ferozHandler1);
			
		// Feroz level 2
		Button ferozBtn2 = new Button();
		ferozBtn2.setText("2");
		grid.add(ferozBtn2, 3, 2);
		FerozHandlerLevel ferozHandler2 = new FerozHandlerLevel(path, 10);
		ferozBtn2.setOnAction(ferozHandler2);

		// Feroz level 3
		Button ferozBtn3 = new Button();
		ferozBtn3.setText("3");
		grid.add(ferozBtn3, 4, 2);
        FerozHandlerLevel ferozHandler3 = new FerozHandlerLevel(path, 11);
        ferozBtn3.setOnAction(ferozHandler3);
		
        // Feroz level 4
		Button ferozBtn4 = new Button();
		ferozBtn4.setText("4");
		grid.add(ferozBtn4, 5, 2);
        FerozHandlerLevel ferozHandler4 = new FerozHandlerLevel(path, 12);
        ferozBtn4.setOnAction(ferozHandler4);
		
		// Feroz level 5
		Button ferozBtn5 = new Button();
		ferozBtn5.setText("5");
		grid.add(ferozBtn5, 6, 2);
        FerozHandlerLevel ferozHandler5 = new FerozHandlerLevel(path, 13);
        ferozBtn5.setOnAction(ferozHandler5);
		
		// Feroz level 6
		Button ferozBtn6 = new Button();
		ferozBtn6.setText("6");
		grid.add(ferozBtn6, 7, 2);
        FerozHandlerLevel ferozHandler6 = new FerozHandlerLevel(path, 14);
        ferozBtn6.setOnAction(ferozHandler6);
		
		// giulio's games
		Button giulioBtn = new Button();
		grid.add(giulioBtn, 0, 3);
		giulioBtn.setText("Giulio's games");
		GiulioHandlerAll giulioHandlerAll = new GiulioHandlerAll(path);
		giulioBtn.setOnAction(giulioHandlerAll);

		// levels text
		Text giulioLevelsText = new Text();
		giulioLevelsText.setText("Levels:");
		grid.add(giulioLevelsText, 1, 3);
		Text ivanLevelsText = new Text();
		ivanLevelsText.setText("Levels:");
		grid.add(ivanLevelsText, 1, 4);

		// giulio's level 1
		Button giulioBtn1 = new Button();
		grid.add(giulioBtn1, 2, 3);
		giulioBtn1.setText("1");
		GiulioHandlerLevel giulioHandler1 = new GiulioHandlerLevel(path, 1);
		giulioBtn1.setOnAction(giulioHandler1);

		// giulio's level 2
		Button giulioBtn2 = new Button();
		grid.add(giulioBtn2, 3, 3);
		giulioBtn2.setText("2");
		GiulioHandlerLevel giulioHandler2 = new GiulioHandlerLevel(path, 2);
		giulioBtn2.setOnAction(giulioHandler2);

		// giulio's level 3
		Button giulioBtn3 = new Button();
		grid.add(giulioBtn3, 4, 3);
		giulioBtn3.setText("3");
		GiulioHandlerLevel giulioHandler3 = new GiulioHandlerLevel(path, 3);
		giulioBtn3.setOnAction(giulioHandler3);

		// ivan's games
		Button ivanBtn = new Button();
		grid.add(ivanBtn, 0, 4);
		ivanBtn.setText("Ivan's games");
		IvanHandlerAll ivanHandlerAll = new IvanHandlerAll(path);
		ivanBtn.setOnAction(ivanHandlerAll);

		// ivan's level 1
		Button ivanBtn1 = new Button();
		grid.add(ivanBtn1, 2, 4);
		ivanBtn1.setText("1");
		IvanHandlerLevel ivanHandler1 = new IvanHandlerLevel(path, 4);
		ivanBtn1.setOnAction(ivanHandler1);

		// ivan's level 2
		Button ivanBtn2 = new Button();
		grid.add(ivanBtn2, 3, 4);
		ivanBtn2.setText("2");
		IvanHandlerLevel ivanHandler2 = new IvanHandlerLevel(path, 5);
		ivanBtn2.setOnAction(ivanHandler2);

		// ivan's level 3
		Button ivanBtn3 = new Button();
		grid.add(ivanBtn3, 4, 4);
		ivanBtn3.setText("3");
		IvanHandlerLevel ivanHandler3 = new IvanHandlerLevel(path, 6);
		ivanBtn3.setOnAction(ivanHandler3);
		
		// Elias' games
		Button eliasBtn = new Button();
		eliasBtn.setText("Elias' games");
		grid.add(eliasBtn, 0, 5);
		EliasHandlerAll eliasHandlerAll = new EliasHandlerAll(path);
		eliasBtn.setOnAction(eliasHandlerAll);
		
		// levels text
		Text eliasLevelsText = new Text();
		eliasLevelsText.setText("Levels:");
		grid.add(eliasLevelsText, 1, 5);
		
		// Elias level 1
		Button eliasBtn1 = new Button();
		eliasBtn1.setText("1");
		grid.add(eliasBtn1, 2, 5);
		EliasHandlerLevel eliasHandler1 = new EliasHandlerLevel(path, 7);
		eliasBtn1.setOnAction(eliasHandler1);
		
		// Elias level 2
		Button eliasBtn2 = new Button();
		eliasBtn2.setText("2");
		grid.add(eliasBtn2, 3, 5);
		EliasHandlerLevel eliasHandler2 = new EliasHandlerLevel(path, 8);
		eliasBtn2.setOnAction(eliasHandler2);

		// exit button
		Button exitButton = new Button();
		exitButton.setText("Exit");
		grid.add(exitButton, 3, 6, 2, 1);
		exitButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent arg0) {
				stage.close();
				return;
			}
		});

		// set scene
		Scene scene = new Scene(grid, 800, 600);
		stage.setScene(scene);
		stage.show();

	}

}
