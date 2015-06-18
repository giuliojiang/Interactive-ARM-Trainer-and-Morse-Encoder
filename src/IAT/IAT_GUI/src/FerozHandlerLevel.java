
public class FerozHandlerLevel extends FerozHandlerAll {
  public FerozHandlerLevel(String ferozPath, int levelNumber) {
    super(ferozPath);
    command = ferozPath + " " + levelNumber;
  }
}
