import java.util.*;

public class Context {

    private Stack<Double> stack = new Stack<>();
    private Map<String, Double> variables = new TreeMap<>();

    public void pushToStack(Double var) {
        stack.push(var);
    }

    public Double popFromStack() throws EmptyStackException { return stack.pop(); }

    public void peekStack() {
        System.out.println(stack.peek());
    }

    public void setNameVar(String key, Double var) {
        variables.put(key, var);
    }

    public Double popFromNameVar(String key) throws Exception {
        if (!variables.containsKey(key)) {
            throw new Exception("Wrong variable: " + key);
        }
        return variables.get(key);
    }
}