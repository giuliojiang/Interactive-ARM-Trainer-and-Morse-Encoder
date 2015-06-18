
public class FerozHandlerAll extends GiulioHandlerAll {

  public FerozHandlerAll(String ferozPath) {
      super(ferozPath);
      command = ferozPath + " -d";
  }

}
