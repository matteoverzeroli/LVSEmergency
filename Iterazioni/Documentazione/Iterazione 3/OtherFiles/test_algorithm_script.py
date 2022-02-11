class TestAlgorithmn(unittest.TestCase):
    def test_1_db_initialization(self):
        try:
            initialize_database()
        except:
            self.fail("Exception in initializing db")

    def test_2_algorithm(self):
        try:
            algorithm('testalg', True)
        except:
            self.fail("Exception in running algorithm")

    def test_3_fog_RED_and_bw_RED(self):
        result = get_fog_RED_and_bw_RED()
        
        expected = [('BW', 'RED', 1, 'Maltempo in avvicinamento, delta = -7.0'), 
	('FOG', 'RED', 1, 'Rischio nebbia attuale')]

        self.assertEqual(result, expected)

    def test_4_frost_RED_and_bw_NONE(self):
        result = get_frost_RED_and_bw_NONE()
        
        expected = [('BW', 'NONE', 2, 'Pressione in diminuzione, delta = -2.0'), 
	('FROST', 'RED', 2, 'Rischio brina attuale')]

        self.assertEqual(result, expected)

    def test_5_fog_NONE_and_bw_NONE(self):
        result = get_fog_NONE_and_bw_NONE()
        
        expected = [('BW', 'NONE', 3, 'Pressione in diminuzione, delta = -2.0'), 
	('FOG', 'NONE', 3, 'Nessun rischio nè attuale nè previsto')]

        self.assertEqual(result, expected)

    def test_6_fog_WHITE_and_bw_NONE(self):
        result = get_fog_WHITE_and_bw_NONE()
        
        expected = [('BW', 'NONE', 4, 'Pressione in diminuzione, delta = -0.75'), 
	('FOG', 'WHITE', 4, 'Rischio nebbia tra 30 minuti')]

        self.assertEqual(result, expected)

    def test_7_fog_GREEN_and_bw_NONE(self):
        result = get_fog_GREEN_and_bw_NONE()
        
        expected = [('BW', 'NONE', 5, 'Pressione in diminuzione, delta = -0.75'), 
	('FOG', 'GREEN', 5, 'Rischio nebbia tra 20 minuti')]

        self.assertEqual(result, expected)
