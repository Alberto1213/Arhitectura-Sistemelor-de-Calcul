from threading import Lock

class Marketplace:
    
    def __init__(self, queue_size_per_producer):
       
        self.queue_size_per_producer = queue_size_per_producer
        self.prod_count = 0
        self.cart_count = 0
        self.lock = Lock()
        self.products = {}      
        self.carts = {}         

    def register_producer(self):
        
        self.lock.acquire()
        self.prod_count += 1
        self.products[self.prod_count] = []
        aux = self.prod_count
        self.lock.release()
        return aux    


    def publish(self, producer_id, product):
      
        if len(self.products[producer_id]) > self.queue_size_per_producer:
            return False

        self.products[producer_id].append(product)
        return True


    def new_cart(self):
     

        self.lock.acquire()
        cart = []
        self.cart_count += 1
        self.carts[self.cart_count] = cart
        aux = self.cart_count
        self.lock.release()
        return aux    


    def add_to_cart(self, cart_id, product):

        for producer_id in self.products:
            if product in self.products[producer_id]:
                
                self.products[producer_id].remove(product)
                self.carts[cart_id].append((product, producer_id))
                return True

        return False

    def remove_from_cart(self, cart_id, product):

        for curr_product,producer_id in self.carts[cart_id]:
        
            if product == curr_product:

                self.products[producer_id].append(product)
                self.carts[cart_id].remove((curr_product,producer_id))
                return


    def place_order(self, cart_id):

        order =[product for product, _ in self.carts[cart_id]]
        self.carts.pop(cart_id)
        return order

