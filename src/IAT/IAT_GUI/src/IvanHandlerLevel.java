
public class IvanHandlerLevel extends IvanHandlerAll {

	public IvanHandlerLevel(String ivanPath, int levelNumber) {
		super(ivanPath);
		command = ivanPath + " " + levelNumber;
	}

}
