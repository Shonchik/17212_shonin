public class Words implements Comparable<Words> {

    private String word;
    private int count;

    Words(String name, int number) {
        word = name;
        count = number;
    }

    public String getWord() {
        return word;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public int getCount() {
        return count;
    }

    @Override
    public int compareTo(Words word) {
        return Integer.compare(count, word.getCount());
    }

}