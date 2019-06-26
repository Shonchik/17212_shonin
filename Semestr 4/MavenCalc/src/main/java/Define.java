import java.util.List;

public class Define implements CommandClass {

    @Inject(arg = Inject.ArgType.CONTEXT)
    private Context context;

    @Inject(arg = Inject.ArgType.ARGS)
    private List<String> arg;

    @Override
    public void run() {
        if(arg.size() == 3){
            context.setNameVar(arg.get(1), Double.parseDouble(arg.get(2)));
        }else{
            System.out.println("Define: No arguments");
        }
    }
}