
public class GiulioHandlerLevel extends GiulioHandlerAll {
	
	public GiulioHandlerLevel(String giulioPath, int levelNumber) {
		super(giulioPath);
		command = giulioPath + " " + levelNumber;
	}

}
