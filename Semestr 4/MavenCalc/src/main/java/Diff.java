import java.util.List;

public class Diff implements CommandClass {

    @Inject(arg = Inject.ArgType.CONTEXT)
    private Context context;

    @Inject(arg = Inject.ArgType.ARGS)
    private List<String> arg;

    @Override
    public void run() {

        if(1 == arg.size()) {
            try {
                Double a = context.popFromStack();
                Double b = context.popFromStack();
                context.pushToStack(a - b);
            } catch (Exception e) {
                System.out.println("ERROR with diff: " + e);
            }
        } else {
            System.out.println("Diff: No arguments");
        }
    }
}