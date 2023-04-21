"""
This module represents the Consumer.
Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
import time


class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.
        :type carts: List
        :param carts: a list of add and remove operations
        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace
        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available
        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """

        Thread.__init__(self, **kwargs)
        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time
        self.name = kwargs['name']

    def add_product(self, cart_id, product, quantity):
        """
        Add a quantity of products to the cart
        """
        for _ in range(quantity):
            tmp = self.marketplace.add_to_cart(cart_id, product)

            # If the product is not available, try again after a given time
            while tmp is False:
                time.sleep(self.retry_wait_time)
                tmp = self.marketplace.add_to_cart(cart_id, product)

    def remove_product(self, cart_id, product, quantity):
        """
        Remove  quantity of products from the cart
        """

        for _ in range(quantity):
            self.marketplace.remove_from_cart(cart_id, product)

    def run(self):
        for cart in self.carts:
            # Add the cart to the marketplace
            cart_id = self.marketplace.new_cart()

            for request in cart:
                # Get type of request(add or remove), product and quantity
                order = request["type"]
                product = request["product"]
                quantity = request["quantity"]

                if order == "add":
                    self.add_product(cart_id, product, quantity)
                elif order == "remove":
                    self.remove_product(cart_id, product, quantity)

            # Get the final order as a list of Products
            order = self.marketplace.place_order(cart_id)

            # Print the order content in output format
            for product in order:
                print(self.name + " bought " + str(product))
