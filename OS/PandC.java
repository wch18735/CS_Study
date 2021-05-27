import java.util.concurrent.*;

class PandC {
	public static void main(String[] arg) {
		Buffer b = new Buffer(100);
		Producer p = new Producer(b, 10000);
		Consumer c = new Consumer(b, 10000);
		p.start();
		c.start();
		try {
			p.join();
			c.join();
		} catch (InterruptedException e) {}
		System.out.println("Number of items in the buf is " + b.count);
	}
}

class Buffer {
	int[] buf;
	int size;
	int count;
	int in;
	int out;
	Semaphore t_mutex, t_full, t_empty;

	Buffer(int size) {
		buf = new int[size];
		this.size = size;
		count = in = out = 0;

		// synchronization
		t_mutex = new Semaphore(1);
		t_full = new Semaphore(0);
		t_empty = new Semaphore(size);
	}
	void insert(int item) {
		try{
			// decrement empty buffer space 1
			// if there aren't empty spaces, block
			t_empty.acquire();
			t_mutex.acquire();

			buf[in] = item;
			in = (in + 1) % size;
			count++;
			
			// increment filled buffer space 1
			t_mutex.release();
			t_full.release();

		} catch(InterruptedException e)
		{
			
		}
	}

	int remove() {
		try{
			// decrement filled buffer space 1
			// if there aren't any information in buffer, block
			t_full.acquire();
			t_mutex.acquire();

			int item = buf[out];
			out = (out + 1) % size;
			count--;
			
			// increment empty buffer space 1
			t_mutex.release();
			t_empty.release();
			
			// return item
			return item;
		}catch(InterruptedException e){
			return -1;
		}
	}
}

/****** 생산자 ******/
class Producer extends Thread {
	Buffer b;
	int N;
	Producer(Buffer b, int N) {
		this.b = b; this.N = N;
	}
	public void run() {
		for (int i=0; i<N; i++)
			b.insert(i);
	}
}
/****** 소비자 ******/
class Consumer extends Thread {
	Buffer b;
	int N;
	Consumer(Buffer b, int N) {
		this.b = b; this.N = N;
	}
	public void run() {
		int item;
		for (int i=0; i<N; i++)
			item = b.remove();
	}
}