import requests
from time import time


class Funds:
    def __init__(self):
        self.__token = "a2e8e18ad26a079c576038f0ad4fa18ce0d9e415f5bf6f43f89cf3831a0e4685__"
        self.last_update = time()
        self.raw = requests.get(
            f'https://app.myinvestor.es/myinvestor-server/rest/public/fondos/find-fondos?tipo=TODOS&token={self.__token}').json()
        self.clean = [{'isin': self.raw[i]['codigoIsin'], 
                       'name': self.raw[i]['nombre'], 
                       'category': self.raw[i] ['categoria'] if 'categoria' in self.raw[i] else None} for i in range(len(self.raw))]
        self.clean.sort(key = lambda e: e['isin'])

    def update(self):
        if time() - self.last_update > 3600:
            self.last_update = time()
            self.raw = requests.get(
                f'https://app.myinvestor.es/myinvestor-server/rest/public/fondos/find-fondos?tipo=TODOS&token={self.__token}').json()
