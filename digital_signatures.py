class Document():

    def __init__(self):
        self.__people_to_sign = []
        self.__document = None
        self.__people_who_signed = []

    def add_person_to_sign(self, person):
        self.__people_to_sign.append(person)

    def set_document(self, document):
        self.__document = document

    def get_document(self):
        return self.__document
    
    def get_people_who_signed(self):
        return self.__people_who_signed
    
    