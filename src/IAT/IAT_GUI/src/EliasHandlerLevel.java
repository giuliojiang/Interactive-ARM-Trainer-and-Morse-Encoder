/**
 * Created by eb1314 on 15/06/15.
 */
public class EliasHandlerLevel extends EliasHandlerAll {

    public EliasHandlerLevel(String eliasPath, int levelNumber) {
        super(eliasPath);
        command = eliasPath + " " + levelNumber;
    }

}
