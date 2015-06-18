/**
 * Created by eb1314 on 15/06/15.
 */
public class EliasHandlerAll extends GiulioHandlerAll {

    public EliasHandlerAll(String eliasPath) {
        super(eliasPath);
        command = eliasPath + " -m";

    }

}
