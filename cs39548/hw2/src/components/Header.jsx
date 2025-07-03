import { useState } from 'react';
import { Link } from 'react-router-dom';
import { useCart } from './Cart';

const Header = () => {
  const [isMenuOpen, setIsMenuOpen] = useState(false);
  const { getTotalItems } = useCart();

  const toggleMenu = () => {
    setIsMenuOpen(!isMenuOpen);
  };

  return (
    <header className="flex items-center justify-between bg-red-900 text-white w-full px-4 py-4">
      <div className="logo flex items-center gap-3">
        <img src="logo.jpg" alt="Logo" className="h-10 w-10 object-contain" />
        <h1 className="text-2xl font-bold">Bob's Burgers</h1>
      </div>

      <nav className="flex-1 flex justify-end">
        <ul 
          className={`flex gap-8 md:static md:flex-row md:gap-8 absolute top-16 left-0 w-full bg-red-900 md:bg-transparent flex-col items-center md:items-center md:w-auto z-50 ${
            isMenuOpen ? 'flex' : 'hidden'
          } md:flex`}
        >
          <li>
            <Link 
              to="/" 
              className="hover:text-yellow-400 block py-2"
              onClick={() => setIsMenuOpen(false)}
            >
              Home
            </Link>
          </li>
          <li>
            <Link 
              to="/menu" 
              className="hover:text-yellow-400 block py-2"
              onClick={() => setIsMenuOpen(false)}
            >
              Menu
            </Link>
          </li>
          <li>
            <Link 
              to="/about" 
              className="hover:text-yellow-400 block py-2"
              onClick={() => setIsMenuOpen(false)}
            >
              About
            </Link>
          </li>
          <li>
            <Link 
              to="/contact" 
              className="hover:text-yellow-400 block py-2"
              onClick={() => setIsMenuOpen(false)}
            >
              Contact
            </Link>
          </li>
          <li>
            <Link 
              to="/cart" 
              className="hover:text-yellow-400 flex items-center gap-1 py-2 relative"
              onClick={() => setIsMenuOpen(false)}
            >
              <svg xmlns="http://www.w3.org/2000/svg" className="w-5 h-5 inline" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M3 3h2l.4 2M7 13h10l4-8H5.4M7 13L5.4 5M7 13l-2 9m13-9l2 9m-5-9V6a2 2 0 10-4 0v7" />
              </svg>
              Cart
              {getTotalItems() > 0 && (
                <span className="bg-yellow-400 text-red-900 text-xs font-bold rounded-full h-5 w-5 flex items-center justify-center ml-1">
                  {getTotalItems()}
                </span>
              )}
            </Link>
          </li>
        </ul>
        <button 
          onClick={toggleMenu}
          className="md:hidden block focus:outline-none ml-4" 
          aria-label="Open Menu"
        >
          <svg className="w-8 h-8" fill="none" stroke="currentColor" viewBox="0 0 24 24">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M4 6h16M4 12h16M4 18h16"/>
          </svg>
        </button>
      </nav>
    </header>
  );
};

export default Header;
