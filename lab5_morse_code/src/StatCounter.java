import java.util.HashSet;

public class StatCounter {
    private Character symbol;
    private Integer counter = 0;

    public StatCounter(Character symbol){ this.symbol = symbol; }

    public Character getSymbol() { return symbol; }
    public Integer getCounter() { return counter; }

    public void increaseCnt() { ++counter; }
    public void decrease() { --counter; }

    public boolean equals(StatCounter other) {
        return this.symbol.equals(other.symbol) && this.counter.equals(other.counter); // don't need counters compare?
    }

    public native int hashCode();
}
