import { Link } from 'react-router-dom';
import bannerImg from '../assets/banner.webp';

const Home = () => {
  return (
    <section className="relative flex-1 flex items-center justify-center overflow-hidden min-h-[calc(100vh-theme(spacing.16)-theme(spacing.24))]">
      <img 
        src={bannerImg} 
        alt="Restaurant Banner" 
        className="absolute inset-0 w-full h-full object-cover opacity-80" 
      />
      <div className="relative z-10 text-center text-white w-full">
        <div className="inline-block bg-black bg-opacity-60 rounded-lg px-8 py-6">
          <h2 className="text-4xl md:text-5xl font-extrabold drop-shadow-lg">Welcome to Bob's Burgers!</h2>
          <p className="mt-4 text-lg md:text-2xl font-medium drop-shadow-md">Feel free to browse the menu.</p>
          <div className="mt-6 flex justify-center gap-4">
            <Link 
              to="/menu" 
              className="bg-yellow-400 hover:bg-yellow-500 text-black font-semibold px-6 py-2 rounded shadow transition"
            >
              View Menu
            </Link>
            <Link 
              to="/contact" 
              className="bg-white hover:bg-gray-200 text-red-900 font-semibold px-6 py-2 rounded shadow transition"
            >
              Contact Us
            </Link>
          </div>
        </div>
      </div>
    </section>
  );
};

export default Home;
