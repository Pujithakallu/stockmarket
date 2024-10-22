import 'package:flutter_bloc/flutter_bloc.dart';
import '../models/book.dart';

enum SortBy { author, title }

abstract class BookState {}

class BookListState extends BookState {
  final List<Book> books;
  final SortBy sortBy;

  BookListState(this.books, this.sortBy);
}

class BookDetailState extends BookState {
  final Book book;

  BookDetailState(this.book);
}

class BookCubit extends Cubit<BookState> {
  List<Book> _books = [];

  BookCubit() : super(BookListState([], SortBy.author)) {
    _init();
  }

  void _init() {
    
    _books = [
        Book(
        id: '1',
        title: 'Carmer Grit',
        author: 'Sarah Jean Horwitz',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSDQwkEmx2WN9LnOQaoXtBd7gDLJtvf8gH94A&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
      Book(
        id: '2',
        title: 'Memory',
        author: 'Angelina Aludo',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRqMIkCpuhWCktOGCtMm8MugdjbGYul2ZGUxQ&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
      Book(
        id: '3',
        title: 'James and the Giant Peach',
        author: 'Roald Dahl',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS4scBIj66P3VEM4_Avjq0qTNlNIkwXvBwFFA&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
      Book(
        id: '4',
        title: 'Little Women',
        author: 'Louisa May Alcott',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQgK6Qdg9TSd_zskdLB6w6SLi4I_ejm3rwccw&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
      Book(
        id: '5',
        title: 'To Kill a Mockingbird',
        author: 'Harper Lee',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSnIPx3Kdi8CLysd3nLcuohEeAza9vi46J7BA&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
      Book(
        id: '6',
        title: '1984',
        author: 'George Orwell',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSE6UrXG8aj1B_vY6iirSSbFTbgGZFlBIcXLw&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
      Book(
        id: '7',
        title: 'Pride and Prejudice',
        author: 'Jane Austen',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQdSI7xHVhmrFAF2USZtYYih-Ng1Lx-fzuE-Q&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
      Book(
        id: '8',
        title: 'The Great Gatsby',
        author: 'F. Scott Fitzgerald',
        imageUrl: 'https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSISjq22kS59zMCzTT7JGCEkr-HM5ffsXT26g&s/200/300',
        description: 'Aspiring inventor and magicians apprentice Felix Carmer III would rather be tinkering with his latest experiments than sawing girls in half on stage, but with Antoine the Amazifier show a tomato throw away from going under, Carmer is determined to win the cash prize in the biggest magic competition in Skemantis. When fate throws Carmer across the path of fiery, flightless faerie princess Grit (do not call her Grettifrida), they strike a deal. If Carmer will help Grit investigate a string of faerie disappearances, she will use her very real magic to give his mechanical illusions a much-needed boost against the competition. But Carmer and Grit soon discover they are not the only duo trying to pair magic with machine and the combination can be deadly.',
      ),
    ];
    _sortAndEmit(SortBy.author);
  }

  void toggleSort() {
  if (state is BookListState) {
    final currentState = state as BookListState;
    final newSortBy = currentState.sortBy == SortBy.author ? SortBy.title : SortBy.author;
    _sortAndEmit(newSortBy);
  }
}

void _sortAndEmit(SortBy sortBy) {
  List<Book> sortedBooks = List.from(_books);
  if (sortBy == SortBy.author) {
    sortedBooks.sort((a, b) => a.author.compareTo(b.author));
  } else {
    sortedBooks.sort((a, b) => a.title.compareTo(b.title));
  }
  emit(BookListState(sortedBooks, sortBy));
}

  void showBookDetail(Book book) {
    emit(BookDetailState(book));
  }

  void showBookList() {
    if (state is BookListState) {
      _sortAndEmit((state as BookListState).sortBy);
    } else {
      _sortAndEmit(SortBy.author);
    }
  }
}