import java.util.List;

public class Sqrt implements CommandClass {

    @Inject(arg = Inject.ArgType.CONTEXT)
    private Context context;

    @Inject(arg = Inject.ArgType.ARGS)
    private List<String> arg;

    @Override
    public void run() {

        if (1 == arg.size()) {
            try {
                Double a = context.popFromStack();
                context.pushToStack(Math.sqrt(a));
            } catch (Exception e) {
                System.out.println("ERROR with sqrt: " + e);
            }
        } else {
            System.out.println("Sqrt: No arguments");
        }
    }
}