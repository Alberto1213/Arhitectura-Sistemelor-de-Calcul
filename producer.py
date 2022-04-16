from threading import Thread
import time

class Producer(Thread):
   
    def __init__(self, products, marketplace, republish_wait_time, **kwargs):
        
        Thread.__init__(self, **kwargs)
        self.products = products
        self.marketplace = marketplace
        self.republish_wait_time = republish_wait_time
        self.producer_id = self.marketplace.register_producer()

    def run(self):
        while True:
            for prod in self.products:
                product, quantity, waiting_time = prod
                while quantity > 0:
                    running = True
                    while running:
                        published = self.marketplace.publish(self.producer_id, product)
                        if published:
                            running = False
                        else:
                            time.sleep(self.republish_wait_time)
                    time.sleep(waiting_time)
                    quantity -= 1

