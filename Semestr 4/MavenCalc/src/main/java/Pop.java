import java.util.List;

public class Pop implements CommandClass {
    @Inject(arg = Inject.ArgType.CONTEXT)
    private Context context;

    @Inject(arg = Inject.ArgType.ARGS)
    private List<String> arg;

    @Override
    public void run(){
        if(1 == arg.size()) {
            context.popFromStack();
        }else{
            System.out.println("Pop: No arguments");
        }

    }
}