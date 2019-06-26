import java.util.List;

public class Print implements CommandClass {

    @Inject(arg = Inject.ArgType.CONTEXT)
    private Context context;

    @Inject(arg = Inject.ArgType.ARGS)
    private List<String> arg;

    @Override
    public void run() {

        if(1 == arg.size()) {
            context.peekStack();
        } else{
            System.out.println("Print: No arguments");
        }
    }
}