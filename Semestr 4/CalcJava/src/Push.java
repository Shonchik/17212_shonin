import java.util.List;

public class Push implements CommandClass {

    @Inject(arg = Inject.ArgType.CONTEXT)
    private Context context;

    @Inject(arg = Inject.ArgType.ARGS)
    private List<String> arg;

    @Override
    public void run() {

        if (2 == arg.size()) {
            try {
                Double a = Double.parseDouble(arg.get(1));
                context.pushToStack(a);
            } catch (NumberFormatException e) {
                try {
                    Double v = context.popFromNameVar(arg.get(1));
                    context.pushToStack(v);
                } catch (Exception err){
                    System.out.println(err);
                }
            }
        } else {
            System.out.println("Push: No arguments");
        }
    }
}