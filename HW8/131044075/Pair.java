
/**
 * Created by CyberTR on 7.1.2017.
 */
import java.io.Serializable;


public class Pair<K,V> implements Serializable{

    private K key;
    public K getKey() { return key; }
    private V value;
    public V getValue() { return value; }

    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    @Override
    public String toString() {
        return key + "=" + value;
    }

    @Override
    public int hashCode() {
        return key.hashCode() * 13 + (value == null ? 0 : value.hashCode());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o instanceof Pair) {
            Pair mypair = (Pair) o;

			if(key != null && !key.toString().equals(mypair.key))
				return false;
			else if(key == null && mypair.key != null)
				return false;
			else if(value != null && !value.equals(mypair.value))
				return false;
			else if(value == null && mypair.value !=null)
				return false;

            return true;
        }
        return false;
    }
}
