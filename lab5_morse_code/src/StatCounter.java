import java.util.HashSet;

public class StatCounter {
    private final Character symbol;
    private Integer counter = 0;

    public StatCounter(Character symbol){
        this.symbol = symbol;
        counter = 1;
    }

    public Character getSymbol(){
        return symbol;
    }

    public Integer getCounter() {
        return counter;
    }

    public void increaseCnt() {
        ++counter;
    }

    public void decrease() {
        --counter;
    }

    public boolean equals(Object other) {
        if(this == other) {
            return true;
        }
        if (other == null || other.getClass() != this.getClass()) {
            return false;
        }
        StatCounter sc = (StatCounter)other;
        return this.symbol.equals(sc.symbol);
    }

    // or use hashCode realisation from Object class
    public int hashCode() {
        return (int)symbol;
    }
}
