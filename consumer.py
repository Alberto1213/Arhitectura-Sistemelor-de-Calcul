from threading import Thread
import time

class Consumer(Thread):

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        
        Thread.__init__(self, **kwargs)
        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time
        self.name = kwargs['name']



    def add_product(self, cart_id, product, quantity):
    
        for _ in range(quantity):
            while not self.marketplace.add_to_cart(cart_id, product):
                time.sleep(self.retry_wait_time)


    def remove_product(self, cart_id, product, quantity):

        while quantity != 0:
            self.marketplace.remove_from_cart(cart_id, product)
            quantity-=1


    def run(self):
        for cart in self.carts:
            cart_id = self.marketplace.new_cart()

            for cart_item in cart:
                order, product, quantity = cart_item["type"], cart_item["product"], cart_item["quantity"]

                if order == "remove":
                    self.remove_product(cart_id, product, quantity)
                elif order == "add":
                    self.add_product(cart_id, product, quantity)

            order = self.marketplace.place_order(cart_id)
            self.print_products(order)    
    
    def print_products(self, order):
        for product in order:
            print(self.name + " bought " + str(product))
