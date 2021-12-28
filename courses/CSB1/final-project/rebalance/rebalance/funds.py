import requests
from time import time


class Funds:
    def __init__(self):
        self.__token = "a2e8e18ad26a079c576038f0ad4fa18ce0d9e415f5bf6f43f89cf3831a0e4685__"
        self.last_update = time()
        self.raw = requests.get(
            f'https://app.myinvestor.es/myinvestor-server/rest/public/fondos/find-fondos?tipo=TODOS&token={self.__token}').json()
        self.eur = []
        for fund in self.raw:
            if fund['divisasDto']['codigo'] == 'EUR':
                self.eur.append(fund)
        self.basic = [{'isin': self.eur[i]['codigoIsin'], 
                       'name': self.eur[i]['nombre']} for i in range(len(self.eur))]
        self.basic.sort(key = lambda e: e['name'])

    def update(self):
        if time() - self.last_update > 3600:
            self.last_update = time()
            self.raw = requests.get(
                f'https://app.myinvestor.es/myinvestor-server/rest/public/fondos/find-fondos?tipo=TODOS&token={self.__token}').json()
