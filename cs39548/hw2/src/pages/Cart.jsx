import { Link } from 'react-router-dom';
import { useCart } from '../components/Cart';

const Cart = () => {
  const { cart, removeFromCart, increaseQuantity, decreaseQuantity, clearCart, getTotal, getTotalItems } = useCart();

  if (cart.length === 0) {
    return (
      <div>
        <div className="flex items-center justify-center min-h-[40vh]">
          <p className="text-center text-lg font-bold text-white">Your cart is empty.</p>
        </div>
        <div className="flex items-center justify-center min-h-[1vh]">
          <Link 
            to="/menu" 
            className="text-center text-lg text-yellow-400 underline hover:text-yellow-500"
          >
            Order food at the menu here.
          </Link>
        </div>
      </div>
    );
  }

  return (
    <div className="max-w-2xl mx-auto mt-8 bg-white rounded-lg shadow-lg p-8">
      <h2 className="text-3xl font-bold mb-6 text-center text-red-900">Your Cart</h2>
      <div className="space-y-4">
        {cart.map((item, index) => (
          <div key={index} className="flex items-center justify-between bg-red-200 rounded-lg shadow p-4">
            <div>
              <span className="font-semibold text-lg">{item.name}</span>
            </div>
            <div className="flex items-center gap-4">
              <div className="flex items-center gap-2">
                <button 
                  className="bg-gray-500 hover:bg-gray-700 text-white w-4 h-8 rounded-full flex items-center justify-center text-lg font-bold"
                  onClick={() => decreaseQuantity(index)}
                >
                  -
                </button>
                <span className="font-semibold text-lg min-w-[1rem] text-center">
                  {item.quantity || 1}
                </span>
                <button 
                  className="bg-gray-500 hover:bg-gray-700 text-white w-4 h-8 rounded-full flex items-center justify-center text-lg font-bold"
                  onClick={() => increaseQuantity(index)}
                >
                  +
                </button>
              </div>
              <span className="font-bold text-red-900">
                ${((item.price || 0) * (item.quantity || 1)).toFixed(2)}
              </span>
              <button 
                className="bg-red-500 hover:bg-red-700 text-white px-3 py-1 rounded"
                onClick={() => removeFromCart(index)}
              >
                Delete
              </button>
            </div>
          </div>
        ))}
      </div>
      <div className="mt-6">
        <div className="text-right text-lg text-red-900 mb-2">
          Total Items: <span className="font-bold">{getTotalItems()}</span>
        </div>
        <div className="text-right text-xl text-red-900 font-bold">
          Total: <span className="text-yellow-700">${getTotal().toFixed(2)}</span>
          <button 
            onClick={clearCart}
            className="bg-red-700 hover:bg-red-900 text-white px-4 py-2 rounded ml-4"
          >
            Clear Cart
          </button>
        </div>
      </div>
    </div>
  );
};

export default Cart;
